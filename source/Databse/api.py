#!/usr/bin/python
# -*- coding: utf-8 -*-
'''
CSE 145 EEG Data Storage API

@author: Alex Rosengarten
@date: May 18 2015

Table Fields:
    subj_name
    group
    date
    id
    data {
        num_channels
        channel_locations
        sample_rate
        reference
        data
    }


'''

import sqlite3 as lite
import datetime as dt
import json
import sys


class DataStorage:

    #initOrLoadDatabase
    def __init__(self, dbname='eeg_data', tablename='EEG_data'):
        #set target database
        if(('.db' in dbname) == False):
            self.db_name = dbname + '.db'
        else:
            self.db_name = dbname

        self.conn = None
        self.table_name = tablename

        self.conn = lite.connect(self.db_name)

        with self.conn:
            self.cur = self.conn.cursor()

            self.cur.executescript("""
                DROP TABLE IF EXISTS EEG_data;
                CREATE TABLE EEG_data(
                  id INTEGER PRIMARY KEY,
                  group_label VARCHAR(20),
                  subj_name VARCHAR(20),
                  date DATETIME,
                  data BLOB(1000000000)
                ); """)

            self.bootstrapData()
            # Print database version
            # self.cur.execute('SELECT SQLITE_VERSION()')
            # data = self.cur.fetchone()
            # print "SQLite version: %s" % data

    def cleanDatabase(self):
        with self.conn:
            self.cur.execute("DELETE FROM TABLE {}".format(self.table_name))

    def bootstrapData(self):

        sample_data = {
            'num_channels': 8,
            'channel_locations': ["Fp1", "Fp2", "F3", "F4", "C3", "Cz", "C4", "ref"],
            'sample_rate': 250,
            'reference': 8,
            'data': "1,2,3,4,5,6,7,8"
        }

        initdata = (
            ('AlexR','Softies', dt.datetime.today(), json.dumps(sample_data)),
            ('AlexM','Softies', dt.datetime.today(), json.dumps(sample_data)),
            ('MikeW','Hardons', dt.datetime.today(), json.dumps(sample_data)),
            ('MikeL','Hardons', dt.datetime.today(), json.dumps(sample_data)),
            ('RaulP','Hardons', dt.datetime.today(), json.dumps(sample_data))
        )
        with self.conn:
            self.cur.executemany("INSERT INTO {}(subj_name, group_label, date, data) VALUES(?, ?, ?, ?)".format(self.table_name), initdata)
                #sendAllData
    def sendAllData(self):
        with self.conn:
            self.cur.execute("SELECT * FROM {}".format(table_name))

            rows = self.cur.fetchall()

            for row in rows:
                print row
    '''

    #storeLastHourOfData
    def storeLastHourOfData(self):


    #sendLastHourOfData
    def sendLastHourOfData(self):



    #sendAllSegmentsBySubject
    def sendAllSegmentsBySubject(self):

    #sendAllSegmentsByDateRange
    def sendAllSegmentsByDateRange(self):

    #sendAllSegmentsByGroup
    def sendAllSegmentsByGroup(self):
    '''

if __name__ == '__main__':
    DB = DataStorage()
    DB.cleanDatabase()
    DB.bootstrapData()

