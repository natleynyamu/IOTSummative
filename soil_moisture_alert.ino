% Enter your MATLAB Code below
% Read the Soil moisture from the past two weeks.
% Send an email and tell the user to add water if the value
% is in the lowest 10 %.

% Store the channel ID for the Soil moisture sensor channel.
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
alertSubject = sprintf("Irrigation action needed");

% Read the recent data.
moistureData = thingSpeakRead(channelID, 'NumPoints', 1, 'Field', 3, 'ReadKey', readAPIKey);

% Check to make sure the data was read correctly from the channel.
if isempty(moistureData)
    alertBody = 'No data read from sensor';
else
    % setting the threshold values.
    dangerLevelHigh = 620;
    dangerLevelLow = 220;

    % Get the most recent Soil moisture value.
    lastValue = moistureData(end);

    % Set the outgoing message
    if lastValue > dangerLevelHigh
        alertBody = sprintf('Moisture is in level of %0.2f. You should stop irrigation', lastValue);
    elseif (lastValue<dangerLevelLow)
        alertBody = sprintf('Moisture is in level of %0.2f. You should start irrigation', lastValue);
    end
end

% Catch errors so the MATLAB code does not disable a TimeControl if it fails
try
    webwrite(alertUrl, "body", alertBody, "subject", alertSubject, options);
catch someException
    fprintf("Failed to send alert: %s\n", someException.message);
end
