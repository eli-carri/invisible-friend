from classes.friend import Friend
import subprocess
import random
import pandas
import smtplib
import os
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

class Game:
    def __init__(self, num_players):
        self._num_players = num_players
        self._players = []
        self._distributions = []

    def add_friends(self):
        # Read players
        for p in range (self._num_players):
            # PLayer info
            print(f'Adding friend {p}')
            name = input('Name: ')
            email = input('Email address: ')
            message = input('Message to invisible friend: ')
            player = Friend(name, email, message)
            # Add player
            self.__add_player__(player)
            print(f'Player successfully added!')
            player.info()
            print('\n')

    def run_game (self):
        # Shuffle players
        random.shuffle(self._players)
        # Bipartite Matching in C++
        result = subprocess.run(["./allocate.exe"],
                                input = f'{self._num_players}',
                                capture_output=True,
                                text=True,
                                check=True)
        # Result
        if result.returncode == 0:
            self._distributions = result.stdout.split(' ')
            self._distributions.remove('')
            self._distributions = [int(p) for p in self._distributions]
            print(f'Distributions successfully generated!\n')

        else:
            print("Error:")
            print(f'{result.stderr}\n')

    def send_emails (self):
        print('Sign in with your email')
        email = input('Email address: ')
        password = input('App Password: ')
        for p in range(self._num_players):
            friend = self._players[p]
            receiver = self._players[self._distributions[p]]

            self.__send_email__(email, password, friend, receiver)


    @staticmethod
    def __send_email__ (email, password, friend, receiver):
        # Server config
        smtp_server = "smtp.gmail.com"
        smtp_port = 587
        # Message config
        addressee = friend.email()
        subject = "<NO RESPONDER> Amigo Invisible"
        body = ('======================== AMIGO INVISIBLE ========================\n' +
                '¡Felicidades! Sos amig@ invisible de: ' + receiver.name() + '\n' +
                'Te dejó un mensaje: "' + receiver.message() + '"\n' +
                '======================================== ========================')
        message = MIMEMultipart()
        message["From"] = email
        message["To"] = addressee
        message["Subject"] = subject
        message.attach(MIMEText(body, "plain"))

        try:
            # Connect to server
            server = smtplib.SMTP(smtp_server, smtp_port)
            server.starttls()
            server.login(email, password)
            # Send email
            server.sendmail(email, addressee, message.as_string())
            print("Email successfully sended to " + receiver.name())
            # Quit server
            server.quit()

        except Exception as e:
            print(f"Error: {e}")

    def __add_player__ (self, player):
        self._players.append(player)

