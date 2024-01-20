## フロントエンド

### webサーバー側
- 以下のコマンドを動かして、http://127.0.0.1:5000 にアクセス
```
cd frontend
frontend % main.py
```

- 以下のcurlコマンドで更新できていることを確認しています。
curl “http://127.0.0.1:5000/chair?charNo=1&is_used=1”


### SQL側
- mysqlに接続する時の認証情報はよしなに変えてくださいませ。dbはご自身のlocalのdbにて作成する必要ありです。
```
    conn = mysql.connector.connect(
            host = '127.0.0.1',
            user = 'root',
            passwd = 'password',
            db = 'iot-chair-sample'
    )
```


## ardiuno側
