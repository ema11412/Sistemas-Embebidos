#
# Estudiantes
# Emanuel Esquivel
# Roger Valderrama
#

import threading, queue, time

# Signals
an = queue.Queue() # largo
bn = queue.Queue() # dato
cn = queue.Queue() # suma de ceros
dn = queue.Queue() # bandera para saber si un numero viene despues de un cero
en = queue.Queue() # numeros que no son ceros
fn = queue.Queue() # cantidad de ceros
gn = queue.Queue() # ceros que deben escribirse y numeros diferentes de cero
zn = queue.Queue() # indice del array
sn = queue.Queue() # señal para escribir num diferente a 0


array = [0,0,1,0,3] #in

out = [] # Array de salida

# delay de inicio
def Delay0():
    an.put_nowait(0)
    while(True):
        an.put_nowait(zn.get())

#Inicio
def Init():
    c = 1
    a = 0
    while(True):
        if a < len(array):
            bn.put_nowait(array[an.get()])
            zn.put_nowait(c)
            an.put_nowait(zn.get())
            c+=1 
            a+=1
            
# compara si es 0 el numero siguiente del array
def Cond():
    zeros = 0
    while(True):
        bn_ = bn.get()
        if bn_ == 0:
            zeros +=1
        else:
            en.put_nowait(bn_)
            cn.put_nowait(zeros)
            zeros = 0

# escribe cantidad de ceros seguidos
def W_zeros():
    while (True):
        cn_ = cn.get()
        if cn_ != 0:
            fn.put_nowait(cn_)
            cn.put_nowait(0)
            dn.put_nowait(1)
        else:
            dn.put_nowait(0)
            fn.put_nowait(0)

# Compara si es cero o no el siguiente 
def Compare():
    while(True):
        dn_ = dn.get()
        en_ = en.get()
        if dn_ == 1:
            gn.put_nowait(en_)
            sn.put_nowait(0)
        if dn_ == 0:
            sn.put_nowait(1)
            gn.put_nowait(en_)

# Escrribe en el nuevo array
def Deco():
    signal = 0
    while(True):
        fn_ = fn.get()
        gn_ = gn.get()
        signal = sn.get()
        
        if fn_ != 0:
            out.append(fn_)
            fn.put_nowait(0)
        
        if signal == 0:
            out.append(gn_)

        elif signal == 1:
            out.append(0)
            out.append(gn_)

# threads
t1 = threading.Thread(target= Delay0)
t2 = threading.Thread(target= Init)
t3 = threading.Thread(target= Cond)
t4 = threading.Thread(target= W_zeros)
t5 = threading.Thread(target= Compare)
t6 = threading.Thread(target= Deco)
t1.start()
t2.start()
t3.start()
t4.start()
t5.start()
t6.start()

# Print del resultado
while(True):
    print(*out) 
    time.sleep(2)
