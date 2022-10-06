# MIE444-MazeNavigatingRover
Course project to autonomously navigate through a maze and retrieve a wooden block

Make a Github account

Must have Git Bash, Arduino IDE, and preferably Git GUI installed and setup

Open Git Bash and follow these steps to get ssh key (authentication to connect local computer to Github) https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent

enter following commands
`ssh-keygen -t ed25519 -C <YOUR.EMAIL@gmail.com`

Note path used to generate key. For me it was /c/Users/Andre/.ssh/id_ed25519

Run command ` clip < /c/Users/Andre/.ssh/id_ed25519.pub`

Follow this link and click 'New SSH Key'

Choose a name like 'SurfaceBookKey' that is personal to that machine

Click Ctrl-V and the generated SSH key should appear

Save key

Open Git Bash

Navigate (cd) to inside Arduino folder

enter command `mkdir MIE444` to make new folder

On your browser, click the big green code, click SSH, and copy the content of the cell as such: ![image](https://user-images.githubusercontent.com/68564062/194407265-92a315af-f8ea-46d6-bb84-b194fa2f0869.png)

**Read next line carefully**
Type `git clone` add 1 whitespace, right click on the screen, and paste from your clipboard, and press Enter

On Git Bash, type `ls`, and you should see MIE444-MazeNavigatingRover appear as a subdirectory

Now your github is linked to the project. Future steps will show you how to push and pull your progress
