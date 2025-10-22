#for example in PostgreSQL
import psycopg2
CONNECTION_STRING = "postgresql://testuser:test123@localhost:5432/testdb"

connection = psycopg2.connect(CONNECTION_STRING)
cursor = connection.cursor()

# we can also create a function to validate user input in the client side
def validate_username(username):
    if not username.isalnum():
        #check for allowed special characters
        if "@" in username or "." in username:
            return True
        #if it has other special characters, reject it
        return False
    return True
    
def get_user_by_username(username):
    # Use parameterized query to prevent SQL Injection
    # here the user input as a parameter variable rather than directly concatenating it into the SQL query 
    query = "SELECT * FROM public.users WHERE username = %s;"
    cursor.execute(query, (username,))

    #it will treat the input as a literal value rather than executable code
    #it will fetch empty results if the input is malicious
    rows = cursor.fetchall()
    for row in rows:
        print(row)
    return


if __name__ == "__main__":
    user_input = input("Enter username: ")
    if validate_username(user_input):
        get_user_by_username(user_input)
    else:
        print("Invalid username format.")
    cursor.close()
    connection.close()