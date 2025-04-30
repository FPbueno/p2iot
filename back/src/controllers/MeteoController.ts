import { Request, Response } from "express";
import query from "./db";
class MeteoController {
    public async create(req: Request, res: Response): Promise<Response> {
        const { umidade, temperatura, co2, uv} = req.body;
        const r: any = await query(
            "INSERT INTO meteo(umidade,temperatura, co2, uv) VALUES ($1,$2,$3,$4) RETURNING id",
            [umidade, temperatura, co2, uv]
        );
        return res.json(r);
    }
    public async list(_: Request, res: Response): Promise<Response> {
        const r: any = await query(
            "SELECT umidade, temperatura, co2, uv, timestamp FROM meteo ORDER BY timestamp"
        );
        return res.json(r);
    }
}
export default new MeteoController();