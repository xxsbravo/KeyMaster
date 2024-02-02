import Fastify from 'fastify';

const listen_addr = '127.0.0.1';   //The ip address the api is listening for
const listen_port = '8001';      //The port the api is listening port

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
    handler: (req, reply) => 
    {
        return{
            key: `${req.query.key}`
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
