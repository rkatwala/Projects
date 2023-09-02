import mysql.connector

#establishing the connection
conn = mysql.connector.connect(
   user='root', password='Ashin!1234', host='127.0.0.1', database='Dev_Schema')

#Creating a cursor object using the cursor() method
cursor = conn.cursor()

#Retrieving single row
sql = '''SELECT * from books'''

#Executing the query
cursor.execute(sql)

#Fetching 1st row from the table
result = cursor.fetchmany(size =2);
print(result)

cursor.callproc('GetAllBooks')

    # print out the result
for result in cursor.stored_results():
	print(result.fetchall())

#Closing the connection
conn.close()
