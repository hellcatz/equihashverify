# equihashverify
nodejs native binding to check for valid Equihash solutions

## usage:
````javascript
var ev = require('bindings')('equihashverify.node');

var header = Buffer.from(..., 'hex');
var solution = Buffer.from(..., 'hex'); //do not include byte size preamble "fd4005"
var personal = "ZcashPoW";
var hsize = 140;
var n=200;
var k=9;

var isValid = ev.verify(header, solution, personal, n, k, hsize);
console.log(isValid);
````
