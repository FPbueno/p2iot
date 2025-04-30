import query from "./db";
async function init(): Promise<any> {
    return await query(`
        START TRANSACTION;
        DROP TABLE IF EXISTS meteo;
        CREATE TABLE IF NOT EXISTS meteo (
            id serial PRIMARY KEY,
            temp double precision NOT NULL,
            hum double precision NOT NULL,
            timestamp timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
        );
        COMMIT;
    `);
}
init()
    .then((r) => console.log(r))
    .catch((e) => console.log(e));

    // DROP TABLE IF EXISTS meteo;
    // CREATE TABLE IF NOT EXISTS meteo (
    //            id serial PRIMARY KEY,
    //            umidade double precision NOT NULL,
    //            temperatura double precision NOT NULL,
    //             co2 double precision NOT NULL,
    //             UV double precision NOT NULL,
    //            timestamp timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
    //        );