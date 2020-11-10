import Foundation

protocol Addable {
  func add(tx: Transaction) -> Double
}

enum TransactionType {
  case credit
  case debit
}

struct Transaction: Addable {
  var amount: Double
  var type: TransactionType
  
  private func signedAmount() -> Double {
    switch type {
    case .debit:
      return -amount
    default:
      return amount
    }
  }
  
  func add(tx: Transaction) -> Double {
    return signedAmount() + tx.signedAmount()
  }
}

let deposit = Transaction(amount: 100.00, type: .credit)
let withdrawal = Transaction(amount: 50.00, type: .debit)

deposit.add(tx: withdrawal)
