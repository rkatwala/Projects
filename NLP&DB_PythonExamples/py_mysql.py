import mysql.connector

#establishing the connection
conn = mysql.connector.connect(
   user='root', password='Rahul1245', host='localhost', database='Dev_Schema')

#Creating a cursor object using the cursor() method
cursor = conn.cursor()

#Retrieving single row
sql = '''SELECT * from books'''

#Executing the query
cursor.execute(sql)

#Fetching 1st row from the table
result = cursor.fetchmany(size =2);
print(result)

#Closing the connection
conn.close()
