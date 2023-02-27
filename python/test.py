import mysql.connector
import matplotlib 
import matplotlib.pyplot as plt

matplotlib.use('GTK3Agg')

db = mysql.connector.connect(host="localhost",
                    user="Patrick",
                    passwd="Nono@012369",
                    database="testmysql")

cur = db.cursor()

cur.execute("select count(id) nbre from contact group by genre order by genre")
stat=cur.fetchall()
nombre = []
for i in stat:
    nombre.append(i[0])

def make_autopct(values):
    def my_autopct(pct):
        total = sum(values)
        val = int(round(pct*total/100.0))
        return '{p:1.1f}%  ({v:d})'.format(p=pct,v=val)
    return my_autopct

plt.pie(nombre, labels=['Femme','Homme'],autopct=make_autopct(nombre), startangle=90, shadow=True)
plt.title('Statistique de mes contacts')
plt.axis('equal')
plt.show()
