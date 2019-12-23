import { createInterface } from "readline";

const rl = createInterface({
	input: process.stdin,
});

type Face = 'a' | 'j' | 'q' | 'k' | number;
type Suit = 'h' | 'd' | 'c' | 's';
interface Card {
	face: Face;
	suit: Suit;
}

const isStraightFlush = (cards: Card[]): boolean => isFlush(cards) && isStraight(cards);

const faceToValue = (rule: 'lo' | 'hi') => (face: Face): number => {
	switch (face) {
		case 'a': return rule === 'hi' ? 14 : 1;
		case 'j': return 11;
		case 'q': return 12;
		case 'k': return 13;
		default: return +face;
	}
}
const hi = faceToValue('hi');
const lo = faceToValue('lo');
const isSequential = (a: number[]): boolean => {
	for (let i = 1; i < a.length; i++)
		if (a[i - 1] + 1 !== a[i])
			return false;
	return true;
}

const compareAsc = (a: number, b: number): number => {
	if (a < b) return -1;
	if (a > b) return 1;
	return 0;
}
const isStraight = (cards: Card[]): boolean => {
	const hiValues = cards.map(c => hi(c.face)).sort(compareAsc);
	const loValues = cards.map(c => lo(c.face)).sort(compareAsc);
	return isSequential(hiValues) || isSequential(loValues);
}

const isFlush = (cards: Card[]): boolean => {
	for (let i = 1; i < cards.length; i++)
		if (cards[i].suit !== cards[0].suit)
			return false;
	return true;
}

const countFaces = (cards: Card[]): number[] => {
	const count = new Map<Face, number>();
	cards.forEach(c => {
		count.set(c.face, (count.get(c.face) ?? 0) + 1);
	});
	return Array.from(count.values());
}

const isFourOfAKind = (counts: number[]): boolean => counts.includes(4);
const isFullHouse = (counts: number[]): boolean => counts.includes(3) && counts.includes(2);
const isThreeOfAKind = (counts: number[]): boolean => counts.includes(3);
const isTwoPair = (counts: number[]): boolean => counts.filter(c => c === 2).length === 2;
const isPair = (counts: number[]): boolean => counts.includes(2);

const cardRegex = /([ajqk0-9]|10)([hdcs])/;
rl.on('line', (line: string) => {
	const cc = line.trim().split(/\s+/);
	if (cc.length !== 5) return console.log('invalid');

	const cards: Card[] = [];
	for (const c of cc) {
		const result = cardRegex.exec(c);
		if (!result) return console.log('invalid');
		cards.push({face: result[1] as Face, suit: result[2] as Suit});
	}

	if (isStraightFlush(cards)) return console.log('straight-flush');
	const counts = countFaces(cards);
	if (isFourOfAKind(counts)) return console.log('four-of-a-kind');
	if (isFullHouse(counts)) return console.log('full-house');
	if (isFlush(cards)) return console.log('flush');
	if (isStraight(cards)) return console.log('straight');
	if (isThreeOfAKind(counts)) return console.log('three-of-a-kind');
	if (isTwoPair(counts)) return console.log('two-pair');
	if (isPair(counts)) return console.log('one-pair');
	return console.log('high-card');
});
