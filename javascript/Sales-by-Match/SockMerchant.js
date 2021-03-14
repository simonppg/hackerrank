function hasThePair(socksMemory, sock) {
  if(!socksMemory[sock]) { return false } 

  return true
}

function remember(socksMemory, sock) {
  socksMemory[sock] =	true
}

function forgetSock(socksMemory, sock) {
  delete socksMemory[sock]
}

function sockMerchant(_n, ar) {
  var aResult = 0
  var socksMemory = {}

  ar.forEach((current) => {
    if(!hasThePair(socksMemory, current)) {
      remember(socksMemory, current)
      return
    }

    aResult++
    forgetSock(socksMemory, current)
  })

  return aResult
}


var socks1 = [10, 20, 20, 10, 10, 30, 50, 10, 20]
var expectedResult1 = 3
var aResult1 = sockMerchant(socks1.length, socks1)
console.log({expectedResult1, aResult1})

socks1 = [1, 2, 3, 4, 5]
expectedResult1 = 0
aResult1 = sockMerchant(socks1.length, socks1)
console.log({expectedResult1, aResult1})

socks1 = [1,2,1,2]
expectedResult1 = 2
aResult1 = sockMerchant(socks1.length, socks1)
console.log({expectedResult1, aResult1})

socks1 = [1,2,1,2,3,4]
expectedResult1 = 2
aResult1 = sockMerchant(socks1.length, socks1)
console.log({expectedResult1, aResult1})

socks1 = []
expectedResult1 = 0
aResult1 = sockMerchant(socks1.length, socks1)
console.log({expectedResult1, aResult1})
