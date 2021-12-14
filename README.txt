csd4112
Vamvakousis Giorgos

main:
exw ena pinaka me olous tous customers kai enan me pointers stous customers me antistoixeia 1 pros 1 gia na kanw ta threads
ta threads einai panta chef+customers (1+N)
kanoume define posous customers theloume
kanw initialize ta semaphores
ftiaxnw to thread tou Chef
ftiaxnw ta threads twn customers me sleep ana 3, wste na kanei dialeimma
join to chef thread, join ta customers threads
kill ta semaphores kai telos
geniki idea:
an to empty einai 0, kai to chef thread klithei phgainei se busy waiting state
an to full einai 0, kai klithei customer thread tote auto paei se busy waiting kai to control paei se allo thread
ginetai mutex lock gia kathe process
