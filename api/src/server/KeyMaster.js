import Fastify from 'fastify';
import Database from "./Server.js"

const listen_addr = '127.0.0.1';   //The ip address the api is listening for
const listen_port = '8001';      //The port the api is listening port

//Logs all Requests
const fastify = Fastify
({
    logger: true,
});

const database = new Database();

//Indicates the web api is running
fastify.get("/", (req, reply) => 
{
    return{
        status: "running..."
    };
});

fastify.route
({
    method: 'POST',
    url: '/api/upload:key',
    schema: 
    {
        params:
        {
            type: "object",
            properties: 
            {
                key: {type: 'string'}
            },
            required: ["key"],
        },
    },
    handler: async (req, reply) => 
    {  
        try {
            const data = { key: `${req.query.key}` };
            await database.saveKey(data);
            return { success: true, message: 'Key uploaded succesfully' };
          } catch (error) {
            console.error(error);
            return { success: false, message: 'The program encountered an error while uploading' };
          }
    },
});

//Specifies what ip address and port to listen on
fastify.listen({port:listen_port, host:listen_addr}, function(err)
{
    if(err)
    {
        fastify.log.error(err);
        process.exit(1);
    }
});
