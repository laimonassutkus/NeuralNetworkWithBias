clear
close all

% --- management variables ---

% the ammount of data from given data to use for NN training (the rest of data will be used for testing)
training_ammount = 200;

% the ammount of error values to be averaged when showing in graph (2 : given data length)
average_ammount = 10;

% ammount of input data to NN
input_ammount = 10;

% number of epochs for NN to train
epochs_ammount = 2000;

% NN learning speed (if 0 is given, it assumes to use maxlinlr function)
learning_speed_ammount = 0;

% --- management variables ---

% --- prepare data ---

fileName = 'sunspot.txt';
data = load(fileName);

data_length = length(data);

input_data = [];
for i = 1:input_ammount
   input_data = [input_data; data(i:data_length - (input_ammount - i + 1), 2)']; % prepare input data for NN
end
                                                      
prediction_data = data(input_ammount + 1:data_length, 2); % prepare answears data                                   
year_data = data(input_ammount + 1:data_length, 1); % array of years that we are working with
input_data_length = length(input_data);

% --- prepare data ---

figure(1)
grid on
hold on
plot(year_data, prediction_data, 'b-') 
title('The number of sun spots each year')
ylabel('The number of suns spots')
xlabel('Years')

testing_ammount = input_data - 200;

% data for training NN
training_input_data = input_data(:, 1:training_ammount);
training_prediction_data = prediction_data(1:training_ammount)';

testing_input_data = input_data(:, training_ammount + 1:input_data_length);

if learning_speed_ammount == 0
    learning_speed_ammount = maxlinlr(training_input_data, 'bias')
end
 
net = newlin(training_input_data, training_prediction_data, 0, learning_speed_ammount);
net.trainParam.goal = 0.1;
net.trainParam.epochs = epochs_ammount;

net = train(net, training_input_data, training_prediction_data);

output_data = sim(net, training_input_data);
testing_output_data = sim(net, testing_input_data);

maximal_output_value = max([output_data testing_output_data prediction_data']);

figure(2)

% --- plotting value predictions ---

subplot(2, 1, 1)
hold on
grid on

% plot NN predicted values (on which it was trained) from 1700 till 1899
plot(year_data(1:training_ammount), output_data, 'r', 'userdata', 'predicted values')

% plot NN predicted values (on new data on which it was not trained) from 1900 till 2012
plot(year_data(training_ammount + 1:input_data_length), testing_output_data, ...
    'g', 'userdata', 'predicted values with test data')

% plot actual values from 1700 till 2012
plot(year_data(1:input_data_length), prediction_data, 'b', 'userdata', 'actual values')

title('Actual values vs. Predicted values')
xlabel('Years')
ylabel('Sun spot count')
legend(get(gca, 'children'), get(get(gca, 'children'), 'userdata'));
axis([year_data(1) year_data(end) 0, maximal_output_value + 20])

% --- plotting value predictions ---

% --- plotting error values ---

subplot(2, 1, 2)
hold on
grid on

error_values = abs(prediction_data' - [output_data testing_output_data]);

data_slices = floor(input_data_length/average_ammount)
averaged_ammount_middle = floor(average_ammount / 2);
averaged_error_values = zeros(1, data_slices);
for i = 0:data_slices - 1
   averaged_error_values(i + 1) = mean(abs(error_values(i * average_ammount + 1:(i + 1) * average_ammount)));
end

average_error = mean(abs(error_values));

plot1 = bar(year_data, error_values, 'c');
plot2 = line([year_data(1) year_data(end)], [average_error average_error], 'Color', 'red');

sliced_year_data = year_data(averaged_ammount_middle:average_ammount:average_ammount * data_slices);

plot3 = plot(sliced_year_data, averaged_error_values, ...
    'b', 'Linewidth', 1.5);

% pretify graph by adding begining and ending lines
line([year_data(1) year_data(averaged_ammount_middle)], [average_error averaged_error_values(1)], ...
    'Color', 'blue', 'Linewidth', 1.5)
line([sliced_year_data(end) year_data(end)], [averaged_error_values(end) average_error], ...
    'Color', 'blue', 'Linewidth', 1.5)

title('Absolute error values')
xlabel('Years')
ylabel('Error')
legend([plot1 plot2 plot3], {'actual values' 'average error' sprintf('averaged error over %d values', average_ammount)})

% --- plotting error values ---

% --- mean square error ---

MSE = mse([output_data testing_output_data] - prediction_data')

% --- mean square error ---









