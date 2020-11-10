class ApplicationSafeSerializer < ActiveModel::Serializer

  def initialize(*args)
    super(*args)
    force_all_associations_loaded
  end

  #
  # Raises exception if trying to serialize associations that are not loaded
  #
  def force_all_associations_loaded
    assocs = self._associations.keys
    r = assocs.map {|a| {a => object.association(a).loaded? } rescue nil }
    not_loaded = r.reject(&:nil?).select {|k| k.values.first==false }
    raise "#{self.class} does not have all associations loaded. Missing: #{not_loaded}" unless not_loaded.empty?
  end

  protected
  def two_decimals_precision(number)
    sprintf('%.2f', number.to_f)
  end

end