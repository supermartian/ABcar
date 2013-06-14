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
var io = require('socket.io').listen(8000);

io.sockets.on('connection', function (socket) {
    socket.on('move', function (data) {
        wire.writeBytes(0x01, [data.sx], function(err){
            console.log("Servo X to " + data.sx);
        })
        wire.writeBytes(0x02, [data.sy], function(err){
            console.log("Servo Y to " + data.sy);
        })
        wire.writeBytes(0x03, [data.speed], function(err){
            console.log("Speed is  " + data.speed);
        })
        wire.writeBytes(0x04, [data.veer], function(err){
            console.log("Veer is  " + data.veer);
        })
    });
});

var http = require('http');
var express = require('express');
var app = express();
app.use(express.static('./webpages'));
var server = http.createServer(app);
server.listen(8989);

