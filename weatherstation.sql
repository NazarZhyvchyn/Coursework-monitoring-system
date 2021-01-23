drop table weather;

/*==============================================================*/
/* Table: weather                                               */
/*==============================================================*/
create table weather (
   weather_id           SERIAL not null,
   date_time            timestamp           ,
   weather_name         VARCHAR(10)          null,
   temperature          NUMERIC(4,2)         null,
   humidity             NUMERIC(4,2)         null,
   pressure             NUMERIC(10,2)        null,
   dust                 NUMERIC(4)           null,
   uv                   DECIMAL(4,2)         null,
   constraint PK_WEATHER primary key (weather_id)
);
INSERT INTO weather (weather_id, date_time, weather_name, temperature, humidity, pressure, dust, uv)
VALUES (0, '2021-01-19 01:30:34', '1', 1,1,1,1,1);