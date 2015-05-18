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
import sys


class DataStorage:

    #initOrLoadDatabase
    def __init__(self, dbname='eeg_data.db'):
        #set target database
        if(('.db' in dbname) == False):
            self.db_name = dbname + '.db'
        else:
            self.db_name = dbname

        self.conn = None

        try:
            # Connect to databse
            self.conn = lite.connect(self.db_name)

            # Check SQLite verion
            self.cur = self.conn.cursor()
            self.cur.execute('SELECT SQLITE_VERSION()')
            data = self.cur.fetchone()
            print "SQLite version: %s" % data

        except lite.Error, e:
            # print error to console, exit system
            print "Error %s: " % e.args[0]
            sys.exit(1)

        finally:
            #safely close connection
            if self.conn:
                self.conn.close()



    '''#connectToSocket
    def connect(self):

    #storeLastHourOfData
    def storeLastHourOfData(self):


    #sendLastHourOfData
    def sendLastHourOfData(self):

    #sendAllData
    def sendAllData(self):

    #sendAllSegmentsBySubject
    def sendAllSegmentsBySubject(self):

    #sendAllSegmentsByDateRange
    def sendAllSegmentsByDateRange(self):

    #sendAllSegmentsByGroup
    def sendAllSegmentsByGroup(self):
    '''

if __name__ == '__main__':
    DB = DataStorage()

