'use strict'
const express = require('express') ;

const app = express() ;

const { CAddOn } = require('bindings')('addon') ;
// events を継承して on イベントを使えるようにする
const { EventEmitter } = require('events') ;
const { inherits } = require('util') ;
inherits(CAddOn, EventEmitter) ;

const addon = new CAddOn() ;
addon.on('EmitSample1', (msg) =>
{
	console.log(`EmitSample1`) ;
	console.log(`msg : ${msg}`) ;
}) ;

addon.on('EmitSample2', (msg) =>
{
	console.log(`EmitSample2`) ;
	console.log(`msg : ${msg}`) ;
}) ;

// listen
app.listen(55555, () =>
{
	console.log('start. port on 55555.') ;
}) ;

