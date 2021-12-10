// construct a type named endpoint
export interface Endpoint {
    // contain items ip, name, port, cores, frequency, memory, disk, bandwidth
    ip: string;
    name: string;
    port: number;
    cores: number;
    frequency: number;
    memory: number;
    disk: number;
    bandwidth: number;
}