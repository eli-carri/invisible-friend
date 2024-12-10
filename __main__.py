import subprocess
from classes.friend import *
from classes.game import *

num_players = input("Number of players: ")
invisible_friend = Game(num_players)
invisible_friend.run_game()
invisible_friend.send_emails()

print('Thank you for playing <3')