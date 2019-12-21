import { createInterface } from 'readline';

interface Marker {
	name: string;
	location: [number, number];
}

const rl = createInterface({
	input: process.stdin,
	output: process.stdout,
});

let data = '';
rl.on('line', (line: string) => {
	data += line;
});

rl.on('close', () => {
	// NOTE: the provided json file is not valid json, and so I fixed it before using it
	const { markers } = JSON.parse(data) as { markers: Marker[] };
	const [ start, destination ] = markers;
	const [ lat1, lon1 ] = start.location;
	const [ lat2, lon2 ] = destination.location;
	const distance = distanceInKmBetweenEarthCoordinates(lat1, lon1, lat2, lon2);
	const bearing = calculateBearing(lat1, lon1, lat2, lon2);
	const direction = bearingName(bearing);
	const output = JSON.stringify({
		directions: {
			message: 'asdf',
			distance,
			direction,
		},
	});
	console.log(output);
});

// https://stackoverflow.com/questions/365826/calculate-distance-between-2-gps-coordinates
function degreesToRadians(degrees: number) {
	return degrees * Math.PI / 180;
}

function distanceInKmBetweenEarthCoordinates(lat1: number, lon1: number, lat2: number, lon2: number) {
	const earthRadiusKm = 6371;

	const dLat = degreesToRadians(lat2 - lat1);
	const dLon = degreesToRadians(lon2 - lon1);

	lat1 = degreesToRadians(lat1);
	lat2 = degreesToRadians(lat2);

	const a = Math.sin(dLat / 2) * Math.sin(dLat / 2) +
			  Math.sin(dLon / 2) * Math.sin(dLon / 2) * Math.cos(lat1) * Math.cos(lat2);
	const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
	return earthRadiusKm * c;
}

function radiansToDegrees(radians: number) {
	return radians * 180 / Math.PI;
}

function calculateBearing(lat1: number, lon1: number, lat2: number, lon2: number) {
	const dLon = degreesToRadians(lon2 - lon1);

	lat1 = degreesToRadians(lat1);
	lat2 = degreesToRadians(lat2);

	const y = Math.sin(dLon) * Math.cos(lat2);
	const x = Math.cos(lat1) * Math.sin(lat2) -
			  Math.sin(lat1) * Math.cos(lat2) * Math.cos(dLon);
	return radiansToDegrees(Math.atan2(y, x));
}

const bearings = ['NE', 'E', 'SE', 'S', 'SW', 'W', 'NW', 'N'];
function bearingName(bearing: number) {
	let index = bearing - 22.5;
	if (index < 0) {
		index += 360;
	}
	index = Math.floor(index / 45);
	return bearings[index];
}
