const p1 = Promise.resolve(111);
const p2 = 22;
const p3 = new Promise((resolve, reject) => { setTimeout(resolve, 1000, 33); });

const withLogging = function(f, prefix) {
	var result;
  return function(...args) {
  	result = f(...args)
    console.log(prefix, result)
    return result
  }
}
const liftP = (func) => (...args) => Promise.all(args).then((values) => func(...values))

let sum = (...args) => args.reduce((i, acc) => acc += i)
let sumP = liftP(withLogging(sum, "Lifted"))

console.log("Plain numbers", sum(111, 222, 333))
Promise.all([p1, p2, p3]).then((values) => console.log("Manual", sum(...values)))
sumP(p1, p2, p3)
