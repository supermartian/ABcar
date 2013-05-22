#!/usr/bin/node
/*
 * test.js
 * Copyright (C) 2013 Wen Yuzhong <supermartian@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

var i2c = require('i2c');
var address = 0x32;     // The arduino side is registered at 0x32
var wire = new i2c(address, {device: '/dev/i2c-1'}); // Point to your i2c address

setInterval(function(){                 // Move the servo constantly
    for (var i = 30; i < 120; i++) {
    wire.writeBytes(0x01, [i], function(err) {
        console.log("Move X");
    });
    wire.writeBytes(0x02, [i], function(err) {
        console.log("Move Y");
    });
}}, 2000);
