import threading
import CCMysql

#所有连接保存在字典里
dsocket={}
#sql
mysql = CCMysql.CCmysql('localhost', 3306, 'chat',   'root', '170525')



#  登录多线程
def ccClient(clinesocket,addr):
    thread1 = threading.Thread(target=add, name='add', args=(clinesocket, addr))  # 线程对象.
    thread1.start()  # 启动.

#thread
def add(clinesocket, addr):
    myrecv = clinesocket.recv(2048).decode('utf-8', 'ignore')
    # que ren fan hui gei he fu duan
    mylist = str(myrecv).split('%')
    print(myrecv, mylist[0],mylist[1],mylist[2])
    print(mylist)
    #保存连接
    dsocket[mylist[0]]=clinesocket
    #先判断是注册还是登录
    if mylist[2]=='zhuce':
        # 注册检查
        if ccChect(mylist[0], mylist[1]) == []:
            sql ="INSERT INTO users ( users_name, users_passwd) VALUES( '%s','%s');"%(mylist[0],mylist[1]);
            print(sql)
            returin = mysql.insert(sql)
            print(returin)
            data = 'zhuceok'
            clinesocket.send(data.encode('utf-8'))
        else:
            data = 'zhuceno'
            clinesocket.send(data.encode('utf-8'))

    elif mylist[2]=='denglu':
        # 登录检查
        print(ccChect(mylist[0], mylist[1]),'hahai')
        if ccChect(mylist[0], mylist[1]) != []:
            data = 'ok'
            clinesocket.send(data.encode('utf-8'))
            # clinesocket.close();
            #检查是否在线或者已经登录过
            if mylist[0] in dsocket.keys():
                pass
            else:
               dsocket[mylist[0]] = clinesocket

        else:
            data = 'no'
            clinesocket.send(data.encode('utf-8'))
            clinesocket.close()

        # pass
    elif mylist[2]=='tainjia':
        if mylist[0]=='':
            data = 'error'
            clinesocket.send(data.encode('utf-8'))
            clinesocket.close()
        else:
            # sql = "CREATE TABLE IF NOT EXISTS `users`( `users_id` INT UNSIGNED AUTO_INCREMENT, `users_name` VARCHAR(100) NOT NULL, `users_passwd` VARCHAR(40) NOT NULL, `submission_date` DATE, PRIMARY KEY ( `users_id` )) DEFAULT CHARSET=utf8"
            # mylist = mysql.get_one(sql)
            name=mylist[0]
            sql = "SELECT * FROM users WHERE users_name='%s';" % (name)
            print(sql)
            returin = mysql.get_all(sql)
            if returin ==[]:
                print(returin)
                # print(mylist)
                data = 'no'
                clinesocket.send(data.encode('utf-8'))
                clinesocket.close()
            elif returin !=[]:
                print(returin)
                # print(mylist)
                data = 'ok'
                clinesocket.send(data.encode('utf-8'))
                clinesocket.close()
    elif mylist[2]=='fangsong':
        print(mylist[2],mylist[3])
        #判断接收方是在线
        if mylist[3] in dsocket.keys():
            data = mylist[1]
            dsocket[mylist[3]].send(data.encode('utf-8'))
            print(data)
            print(mylist[3])
            print(type(dsocket[mylist[3]]))
    print(dsocket)


   #查找成功返回returin
def ccChect(name,passwd):
    sql = "CREATE TABLE IF NOT EXISTS `users`( `users_id` INT UNSIGNED AUTO_INCREMENT, `users_name` VARCHAR(100) NOT NULL, `users_passwd` VARCHAR(40) NOT NULL, `submission_date` DATE, PRIMARY KEY ( `users_id` )) DEFAULT CHARSET=utf8"
    mylist = mysql.get_one(sql)
    print(mylist)
    sqlname = name
    sqlmima = passwd
    print(name,passwd)
    sql = "SELECT * FROM users WHERE users_name='%s' and users_passwd='%s';"%(name,passwd)
    print(sql)
    returin = mysql.get_all(sql)
    print(returin)
    #pan duan shifou zhice
    return returin
    # sql="SELECT * FROM users;"
    # returin=mysql.get_all(sql)
    # print(returin)


if __name__ == '__main__':

    sql ="CREATE TABLE IF NOT EXISTS `users`( `users_id` INT UNSIGNED AUTO_INCREMENT, `users_name` VARCHAR(100) NOT NULL, `users_passwd` VARCHAR(40) NOT NULL, `submission_date` DATE, PRIMARY KEY ( `users_id` )) DEFAULT CHARSET=utf8"
    mylist=mysql.get_one(sql)
    print(mylist)
    name='zhazhahui'
    mima = '123'
    sql="INSERT INTO users( users_name, users_passwd ) VALUES ('%s','%s');"%(name,mima)
    sql = "INSERT INTO users( users_name, users_passwd ) VALUES ('%s','%s');" % (name, mima)
    returin=mysql.insert(sql)
    sql="SELECT * FROM users;"
    returin=mysql.get_all(sql)
    #sql ="CREATE TABLE IF NOT EXISTS `users`( `users_id` INT UNSIGNED AUTO_INCREMENT, `users_name` VARCHAR(100) NOT NULL, `users_passwd` VARCHAR(40) NOT NULL, `submission_date` DATE, PRIMARY KEY ( `users_id` )) DEFAULT CHARSET=utf8"
    print(returin)

def onetonechat(name,namesocket):
    pass
#  聊天多线程
def ccOneChatThread(name,namesocket):
    thread1 = threading.Thread(target=add, name='onetonechat', args=(name, namesocket))  # 线程对象.
    thread1.start()  # 启动.