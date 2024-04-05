% Enter your MATLAB Code below
% Read the temperature from the past two weeks.
% Send an email and tell the user to add water if the value
% is in the lowest 10 %.

% Store the channel ID for the temperature sensor channel.
channelID = 2492954;

% Placeholder for your Read API Key
readAPIKey = '0F280LMFOAL96UKW'; % Replace YOUR_READ_API_KEY_HERE with your actual Read API Key

% Provide the ThingSpeak alerts API key.  All alerts API keys start with TAK.
alertApiKey = 'TAKMQY9wpcBDdK/OIya';

% Set the address for the HTTP call
alertUrl = "https://api.thingspeak.com/alerts/send";

% webwrite uses weboptions to add required headers.  Alerts needs a ThingSpeak-Alerts-API-Key header.
options = weboptions("HeaderFields", ["ThingSpeak-Alerts-API-Key", alertApiKey]);

% Set the email subject.
alertSubject = sprintf("Temperature Alert: Action Required on Farm");

% Read the recent data.
Temperature = thingSpeakRead(channelID, 'NumDays', 1, 'Field', 1, 'ReadKey', readAPIKey);

% Check to make sure the data was read correctly from the channel.
if isempty(Temperature)
    alertBody = 'No data read from sensor';
else
    % setting the threshold values.
    minValue = 15;
    maxValue = 26;

    % Get the most recent temperature value.
    lastValue = Temperature(end);

    % Set the outgoing message
    if lastValue <= minValue
        alertBody = sprintf('Dear Sindy, the ThingSpeak system has detected a change in temperature on your farm to a value below 15°C, and we require your immediate action. This temperature fall poses a risk to your crops and livestock. We, therefore, advise you to close any open spaces that allow cold air in to prevent potential damage on your farm. Please take necessary actions! Current Temperature: %.2f°C', lastValue);
    elseif lastValue > maxValue
        alertBody = sprintf('Dear Sindy, the ThingSpeak system has detected an increase in temperature on your farm to a value above 26°C, and we require your immediate action. This temperature increase poses a risk to your crops and livestock. We, therefore, advise you to open any enclosed spaces to prevent potential damage on your farm. Please take necessary actions! Current Temperature: %.2f°C', lastValue);
    else
        alertBody = sprintf('No action required. Current Temperature: %.2f°C', lastValue);
    end
end

% Catch errors so the MATLAB code does not disable a TimeControl if it fails
try
    webwrite(alertUrl, "body", alertBody, "subject", alertSubject, options);
catch someException
    fprintf("Failed to send alert: %s\n", someException.message);
end
