WITH temp AS (
  SELECT
    pages.channel,
    COUNT(1) OVER(PARTITION BY pages.universal_id) AS num_touches,
    ROW_NUMBER() OVER(PARTITION BY pages.universal_id ORDER BY pages.timestamp ASC) AS row_num_asc,
    ROW_NUMBER() OVER(PARTITION BY pages.universal_id ORDER BY pages.timestamp DESC) AS row_num_desc
  FROM looker_scratch.LR_DWVEKBX0ON1Y528HCNO7G_pages_with_uids_and_sessions_and_chann AS pages
  WHERE pages.channel != 'Internal'
  LIMIT 1000
)
SELECT 
  channel,
  COUNTIF(row_num_asc = 1) AS first,
  COUNTIF(row_num_desc = 1) AS last,
  SUM(1/num_touches) AS linear
FROM temp
GROUP BY 1