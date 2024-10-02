from masha import Masha
from peter import Peter

masha = Masha(grow=160)
peter = Peter(grow=170)

masha.changeGrow(change=5)
peter.changeGrow(change=3)

print(f"{'-'*5} Маша {'-'*5}")
print(masha.colorEye())
masha.printGrow()

print(f"{'-'*5} Петя {'-'*5}")
print(peter.colorEye())
peter.printGrow()
