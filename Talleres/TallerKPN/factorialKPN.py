import queue
import threading
import time


#Señales
an = queue.Queue()
bn = queue.Queue()
cn = queue.Queue()
dn = queue.Queue()
en = queue.Queue()
fn = queue.Queue()
gn = queue.Queue()
hn = queue.Queue()




def delay1():
  cn.put(1)
  while True:
    a = cn.get()
    dn.put(a)

def delay2():
  fn.put(1)
  while True:
    a = fn.get()
    gn.put(a)


#SEPARACIONES-*---
def split1():
  while True:
    a = dn.get()
    en.put(a)
    bn.put(a)

def split2():
  while True:
    a = hn.get()
    an.put(a)
    fn.put(a)
#SEPARACIONES-*---



#SUMA
def add():
  a = 0
  c = 0
  while True:
    a = gn.get()
    c = a + 1
    hn.put(c)


#multiplicacion
def mul():
  a = 0
  b = 0
  c = 0

  while True:
    a = an.get()
    b = bn.get()
    c = a * b
    cn.put(c)


Delay1 = threading.Thread(target=delay1).start()
Delay2 = threading.Thread(target=delay2).start()
Split1 = threading.Thread(target=split1).start()
Split2 = threading.Thread(target=split2).start()


Add = threading.Thread(target=add).start()
Mul = threading.Thread(target=mul).start()

while True:
  print(str(en.get()))
  time.sleep(1)



