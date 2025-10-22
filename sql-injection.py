#for example in PostgreSQL
import psycopg2
CONNECTION_STRING = "postgresql://testuser:test123@localhost:5432/testdb"

connection = psycopg2.connect(CONNECTION_STRING)
cursor = connection.cursor()

def get_user_by_username(username):
    # Vulnerable to SQL Injection
    #here the username from user input is directly concatenated into the SQL query 
    #an attacker may input something like: ' OR '1'='1 and it will return all users
    #if the connected user has sufficient privileges, they could even drop tables or modify data
    query = f"SELECT * FROM public.users WHERE username = '{username}';"
    cursor.execute(query)
    rows = cursor.fetchall()
    for row in rows:
        print(row)
    return


if __name__ == "__main__":
    user_input = input("Enter username: ")
    get_user_by_username(user_input)
    cursor.close()
    connection.close()