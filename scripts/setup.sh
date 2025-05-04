#!/bin/bash -evx

sudo cp trainee_joy_secret_command.service /etc/systemd/system/trainee_joy_secret_command.service
sudo systemctl daemon-reload
sudo systemctl enable trainee_joy_secret_command.service
sudo systemctl restart trainee_joy_secret_command.service