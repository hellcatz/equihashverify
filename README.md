# equihashverify
nodejs native binding to check for valid Equihash solutions

## usage:
````javascript
var ev = require('equihashverify');

var header = new Buffer(..., 'hex');
var solution = new Buffer(..., 'hex'); //do not include byte size preamble "fd4005"
var personal = "ZcashPoW";
var hsize = 140;
var n=200;
var k=9;

var isValid = ev.verify(header, solution, personal, n, k, hsize);
console.log(isValid);
````
