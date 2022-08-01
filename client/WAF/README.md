# Instructions
To use the program, we need to run these commands in the terminal:

1.sudo su

2.iptables-A INPUT-j NFQUEUE --queue-num 1

3.When we finish with the program and we don't want to use it any more, we put this command: iptables-F
