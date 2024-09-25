k = 0
for i in range(100, 1000):
    if i % 15 == 0 and i % 30 != 0:
        print(i)
        k += 1
print(k)

# start

# block`k = 0`

# for`i = 100(1)1000` {
#     if`i%15 ==0
# and
# i%30 !=0` then(да) {
#         io`Вывод: i`
#         block`k += 1`
#     }
# }

# io`Вывод: k`
# stop
