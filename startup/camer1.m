clear;
sp=actxserver('SAPI.SpVoice');
camera=webcam(2); %connect to camera
nnet=alexnet;%load neural network,alexnet is a CNN,artist train it as millison of picture
%make a circle to reload frame from camera
while true
picture=camera.snapshot;
picture=imresize(picture,[227,227]);%resize picture
picture=imrotate(picture, -90);
label=classify(nnet,picture);%
image(picture);
title(char(label));
sp.Speak(char(label));
drawnow;
end