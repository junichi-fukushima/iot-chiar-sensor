from flask import Flask, render_template, request
import mysql.connector

app = Flask(__name__)

def conn_db():
    conn = mysql.connector.connect(
            host = '127.0.0.1',
            user = 'root',
            passwd = 'password',
            db = 'iot-chair-sample'
    )
    return conn


@app.route('/')
def index():
    chairs = []
    try:
        sql = 'SELECT * FROM chairs'
        conn = conn_db()
        cursor = conn.cursor()
        cursor.execute(sql)
        rows = cursor.fetchall()
        for row in rows:
            chair = {"id": row[0], "charNo": row[1], "is_used": row[2]}
            chairs.append(chair)
        print('DBからの値の取得に成功しました。')
    except(mysql.connector.errors.ProgrammingError) as e:
        print('DB接続時にエラーが発生しました。')
        print(e)

    return render_template('index.html', chairs=chairs)

@app.route('/chair', methods=['GET'])
def update_chair():
    char_no = request.args.get('charNo')
    is_used = request.args.get('is_used')

    # パラメータの検証（オプショナル）
    if not char_no or not is_used:
        return "charNo と is_used は必須です", 400

    try:
        conn = conn_db()
        cursor = conn.cursor()

        # chairs テーブルを更新
        sql = "UPDATE chairs SET is_used = %s WHERE charNo = %s"
        cursor.execute(sql, (is_used, char_no))
        conn.commit()

        return "チェアの状態が更新されました", 200
    except mysql.connector.Error as e:
        return f"データベースエラー: {e}", 500
    finally:
        if conn:
            conn.close()


if __name__ == '__main__':
    app.run(debug=True)
