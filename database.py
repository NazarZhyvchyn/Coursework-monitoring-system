'''
This contains database functions. create_table will create the
table if it does not exist. The insert_data function inserts data
into the database.
'''

import os
import psycopg2

database_url = 'postgres://postgres:1111@localhost:5432/weatherstation'



def create_table():
    '''Create table in database'''

    try:
        conn = psycopg2.connect(database_url)
        cur = conn.cursor()
        cur.execute('''CREATE TABLE IF NOT EXISTS sensor_data (
            weather_id serial  ,
            date_time TIMESTAMP NOT NULL,
            weather_name VARCHAR(50),
            temperature REAL NOT NULL,
            humidity REAL NOT NULL,
            pressure REAL NOT NULL,
            dust REAL NOT NULL,
            uv REAL NOT NULL
            )''')
        conn.commit()
    except Exception as e:
        print(e)
        return


def insert_data( date_time, sensor1, sensor2, sensor3, sensor4):
    '''Insert data into database'''

    conn = psycopg2.connect(database_url)
    cur = conn.cursor()
    cur.execute('''INSERT INTO weather (
         date_time, temperature, humidity, pressure, dust, uv) VALUES (
         %s, %s,  %s, %s,  %s, %s)''', ( date_time, sensor1, sensor2, sensor3, 0, sensor4))
    conn.commit()
    conn.close()



create_table()
