To use the program we need to run those commands in the terminal:

1.sudo su
2.iptables -A INPUT -j NFQUEUE --queue-num 1
3.when we finish with the program and we don't to use it any more we put this command iptables -F
