#!/bin/bash

sudo su -l postgres -c "psql -d $DB_NAME -c 'SELECT * FROM trading_cards'"
