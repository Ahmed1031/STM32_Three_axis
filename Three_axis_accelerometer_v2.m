%%%%%%%%%%%%%%%%%
% load Package
pkg load instrument-control;

% Create serial port object
s = serialport("COM6", 115200);

% Preallocate arrays
N = 200;
X = zeros(1, N);
Y = zeros(1, N);
Z = zeros(1, N);

% Variables to hold GPS coordinates
gpsLat = "";
gpsLon = "";

% Helper function: convert NMEA (ddmm.mmmm) to decimal degrees
function decDeg = nmea2decimal(coordStr, dir)
    if isempty(coordStr)
        decDeg = NaN;
        return;
    end
    val = str2double(coordStr);
    deg = floor(val / 100);
    minutes = val - deg*100;
    decDeg = deg + minutes/60;
    if dir == 'S' || dir == 'W'
        decDeg = -decDeg;
    end
end



% Read and parse data
idx = 1;
 while idx <= N
    line = readline(s);
    tokens = regexp(line, 'X-axis\s*:\s*(\d+)\s*,\s*Y-axis\s*:\s*(\d+)\s*,\s*Z-axis\s*:\s*(\d+)', 'tokens');
    if ~isempty(tokens)
        values = str2double(tokens{1});
        X(idx) = values(1);
        Y(idx) = values(2);
        Z(idx) = values(3);
        idx = idx + 1;   % only increment when valid accelerometer data
     end


    % Parse GPS coordinates from $GPRMC sentence
    gpsTokens = regexp(line, '\$GPRMC,[^,]*,[^,]*,([^,]*),([NS]),([^,]*),([EW])', 'tokens');
    if ~isempty(gpsTokens)
        latRaw = gpsTokens{1}{1};
        latDir = gpsTokens{1}{2};
        lonRaw = gpsTokens{1}{3};
        lonDir = gpsTokens{1}{4};

        % Convert to decimal degrees
        latDec = nmea2decimal(latRaw, latDir);
        lonDec = nmea2decimal(lonRaw, lonDir);

        % Format nicely
        gpsLat = sprintf("%.6f° %s", abs(latDec), latDir);
        gpsLon = sprintf("%.6f° %s", abs(lonDec), lonDir);
    end
end

% Plot results
figure;
plot(1:nnz(X), X(1:nnz(X)), 'r-', 'DisplayName', 'X-axis');
hold on;
plot(1:nnz(Y), Y(1:nnz(Y)), 'g-', 'DisplayName', 'Y-axis');
plot(1:nnz(Z), Z(1:nnz(Z)), 'b-', 'DisplayName', 'Z-axis');
xlabel('Sample Index');
ylabel('Sensor Values');
title('Data from COM6');
legend show;
grid on;

% Add GPS coordinates at bottom center
if ~isempty(gpsLat) && ~isempty(gpsLon)
    coords = sprintf("GPS: %s , %s", gpsLat, gpsLon);
    text(0.5, -0.1, coords, 'Units','normalized', ...
         'HorizontalAlignment','center', 'VerticalAlignment','top', ...
         'FontWeight','bold');
end


