//All functions interacting with the server locally should be stored here

import * as fs from 'node:fs/promises';

export default class Database {
    async saveKey(data)
    {
        try
        {
            await fs.writeFile('../../../assets/key.json', JSON.stringify(data));
        }catch(error)
        {
            console.error(error);
        }
    }
}