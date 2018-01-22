# Controls-PID Implementation
I wrote my twiddle version based on what was presented. I created a Twiddle-mode, when my algo will reset the simulator everytime the car runs out of the track, or if there are enough iterations of good driving done. I am able to get very good result, the final PID params chosen are:
P:0.128	I:0.0001 D:7.22

# Reflection

Following describes the effect of the P, I, D component of the PID algorithm:

P: Proportional Term
Quick movement to reduce the error faster.
![alt text](PZero.mov "Proportional Zero")

D: Derivate Term
For smoother movement, this is making the car turn in smoother movements.
![alt text](DZero.mov "Derivate Zero")

I: Integrate Term
Even smoother movement than the D term.
![alt text](IZero.mov "Integrate Zero")

How the final hyperparameters were chosen:

For initial starting values, I took the twiddle algorithm values from the quiz run: P = 2.9, I = 0.5, D = 10.0.  Then I wrote code to run the code in Twiddle mode: `pid.twiddle_mode`. In Twiddle mode the code will run `5000` iterations or if the Cross Track Error is too large. In Twiddle mode, I run the Twiddle algorithm to fine tune the PID co-effecients.  The following shows a sample output of this algorigth, as it tries to find the best value.

Note: everytime the algo runs for more than 5000 iterations or runs out of the lane, it will restart.


```Twiddle=> best PID Co-effecients 	P:2.9	I:0.5	D:10
Twiddle=> trying with PID Co-effecients 	P:4	I:1.6	D:11.1
Twiddle=> error: 0.260369
Twiddle=> reducing PID Co-effecients 	P:1.8	I:-0.6	D:8.9
Twiddle=> trying with PID Co-effecients 	P:1.8	I:0	D:8.9
Twiddle=> error: 0.00413992
Twiddle=> reducing Twiddle Co-effecients 	P:0.99	I:0.99	D:0.99
Twiddle=> trying with PID Co-effecients 	P:2.9	I:1.1	D:10
Twiddle=> error: 0.114802
Twiddle=> reducing PID Co-effecients 	P:0.92	I:-0.88	D:8.02
Twiddle=> trying with PID Co-effecients 	P:0.92	I:0	D:8.02
Twiddle=> error: 0.00548854
Twiddle=> reducing Twiddle Co-effecients 	P:0.891	I:0.891	D:0.891
Twiddle=> trying with PID Co-effecients 	P:1.91	I:0.99	D:9.01
Twiddle=> error: 0.114802
Twiddle=> reducing PID Co-effecients 	P:0.128	I:-0.792	D:7.228
Twiddle=> trying with PID Co-effecients 	P:0.128	I:0	D:7.228
Twiddle=> error: 6.16133e-06
Twiddle=> reducing Twiddle Co-effecients 	P:0.8019	I:0.8019	D:0.8019
Twiddle=> trying with PID Co-effecients 	P:1.019	I:0.891	D:8.119
Twiddle=> error: 0.115226
Twiddle=> reducing PID Co-effecients 	P:-0.5848	I:-0.7128	D:6.5152
Twiddle=> trying with PID Co-effecients 	P:0	I:0	D:6.5152```



# Simulation
Using the above algo, I was able to get these values, with the smallest error:

```Twiddle=> trying with PID Co-effecients 	P:0.128	I:0	D:7.22
Twiddle=> error: 6.16133e-06```

I then added a small value to I term: 0.0001, with these values I am able to get very good results, I was able to run the whole track without any tire leaving the drivable portion of the track.