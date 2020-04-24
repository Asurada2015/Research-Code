import pymysql

# Loginfo = {
#     'USER': 'root',
#     'PSWD': 'tcqkjjhhh123',
#     'HOST': '172.16.0.5',
#     'PORT': 3306,
#     'DBNAME': 'ParkingLot'
# }

Loginfo = {
    'USER': 'root',
    'PSWD': '0017',
    'HOST': '127.0.0.1',
    'PORT': 3306,
    'DBNAME': 'ParkingLot'
}


def connect_mysql():
    db = pymysql.connect(
        host=Loginfo['HOST'],
        port=Loginfo['PORT'],
        user=Loginfo['USER'],
        passwd=Loginfo['PSWD'],
        db=Loginfo['DBNAME'],
        charset='utf8')
    cursor = db.cursor()
    return db, cursor


def close_mysql(db, cursor):
    cursor.close()
    db.close()
