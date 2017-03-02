clear
close all

fileName = 'sunspot.txt';
S = load(fileName);

L = length(S);
% NN will have two inputs: n -th years spot count and n+1 -th years spot count
P = [S(1:L - 2, 2)'; S(2:L - 1, 2)'];
% NN will have one output predicted spot count. Matrix T is the n+2 -th years spot counts.
T = S(3:L, 2);
Y = S(1:L, 1);

figure(1)
grid on
hold on
plot(Y,S(:,2),'b-') 
title('The number of sun spots each year')
ylabel('The number of suns spots')
xlabel('Years')

figure(2)
grid on
hold on
plot3(P(1,:),P(2,:),T,'bo')
title('Data inputs and outputs');
xlabel('n -th years sun spot count')
ylabel('n+1 -th years sun spot count')
zlabel('Predicted sun spot count')

train_data_count = 200;
test_data_count = L - 200;

% data for training NN
Pu = P(:, 1:train_data_count);
Tu = T(1:train_data_count)';

net = newlind(Pu, Tu);

disp('Neuron weights:'); 
disp(net.IW{1});
disp(net.b{1});

w1 = net.IW{1}(1);
w2 = net.IW{1}(2);
b = net.b{1};

Tsu = sim(net, Pu);
Tsu2 = sim(net, P(:, train_data_count:L - 2));

figure(3)
hold on
grid on

% plot NN predicted values (on which it was trained) from 1700 till 1899
plot(Y(1:length(Tsu)), Tsu, 'r', 'userdata', 'predicted values')

% plot NN predicted values (on new data on which it was not trained) from 1900 till 2012
plot(Y(length(Tsu):L - 2), Tsu2, 'g', 'userdata', 'predicted values with test data')

% plot actual values from 1700 till 2012
plot(Y(1:L - 2), T, 'b', 'userdata', 'actual values')

title('Actual values vs. Predicted values')
xlabel('Years')
ylabel('Sun spot count')
legend(get(gca, 'children'), get(get(gca, 'children'), 'userdata'))








