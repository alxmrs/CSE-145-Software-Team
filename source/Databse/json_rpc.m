function [ response ] = json_rpc( method, params, id, t)
%json-rpc client for json-rpc protocol 
% dependencies: jsonlab-1.0 and jsonrpc2. 
% Make sure to modify the addpaths at top of function.   
addpath('/Users/Xander/Documents/MATLAB/jsonlab-1.0/jsonlab');
addpath('/Users/Xander/Documents/MATLAB/jsonrpc2/jsonrpc2/');



% Check that params is a struct
if ~isstruct(params)
    display('params needs to be a struct!');
    return;
end

% Generate JSON request
request = jsonrpc2.JSONRPC2Request(id, method, params);
json_request = request.toJSONString();
json_request(json_request == char(10)) = ' '; % remove the newline characters from json_request. 
disp(json_request);


if nargin == 3
    disp('Making RPC to default destination: localhost:8888');
    t = createConnection('localhost', 8888);
    try
        fopen(t);
        disp('Connection opened');
    catch ME
        display(ME.identifier);
        display('Safely closing connection');
        fclose(t);
        delete(t);
        rethrow(ME);
    end
end

% set timeout value to be large
set(t,'timeout',20);

try
    disp('Sending json request');
    fwrite(t, json_request);
catch ME
    display(ME.identifier);
    display('Safely closing connection');
    fclose(t);
    delete(t);
    
    rethrow(ME);
end
disp('Request sent successfully.');
disp('Waiting for response...');

json_resp = '';
while(t.BytesAvailable == 0)
end

while(t.BytesAvailable > 0)
    disp('incoming response...');
     try
        json_resp = fread(t, t.BytesAvailable);
    catch ME
        display(ME.identifier);
        display('Safely closing connection');
        fclose(t);
        delete(t);
    %     echopip('off');
%         disp(msg);

        json_resp = savejson('', {'message', 'error with read'});

        rethrow(ME);
     end
end

if(isnumeric(json_resp(1)))
    json_resp = char(json_resp);
end


response = json_resp';%loadjson(json_resp);
disp('recieved:');
disp(response);



end

