import Fastify from 'fastify';
import * as fs from 'node:fs/promises';

const listen_addr = '127.0.0.1';   //The ip address the api is listening for
const listen_port = '8001';      //The port the api is listening port

async function writeKeyToJSON(data)
{
    try
    {
        await fs.writeFile('../../assets/key.json', JSON.stringify(data));
    }catch(error)
    {
        console.error(error);
    }
}

//Logs all Requests
const fastify = Fastify
({
    logger: true,
});

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
            await writeKeyToJSON(data); // Await the execution of writeKeyToJSON
            return { success: true, message: 'Data uploaded and processed successfully' };
          } catch (error) {
            console.error(error);
            return { success: false, message: 'Error processing uploaded data' };
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
