import subprocess
from classes.friend import Friend
from classes.game import Game

num_players = int(input("Number of players: "))
invisible_friend = Game(num_players)
invisible_friend.add_friends()
invisible_friend.run_game()
invisible_friend.send_emails()

print('Thank you for playing <3')