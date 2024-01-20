#  http://127.0.0.1:5000にアクセス
from flask import Flask, render_template
from flask_mysqldb import MySQL

app = Flask(__name__)

# MySQL接続設定
app.config['MYSQL_HOST'] = '127.0.0.1'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = 'password'
app.config['MYSQL_DB'] = 'iot-chair-sample'

mysql = MySQL(app)

@app.route('/')
def index():
    # cursor = mysql.connection.cursor()
    # cursor.execute("SELECT charNo, is_used FROM chairs")  # 'chairs' はテーブル名です
    # chairs = cursor.fetchall()
    # return render_template('index.html', chairs=chairs)
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)
