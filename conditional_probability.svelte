<style type="text/css">
 .debug-item {
	 display: none;
 }

 .visualization-wrapper {
	 display: flex;
	 flex-flow: column nowrap;
	 align-items: center;
	 width: 600px;
	 max-width: 100%;
 }

 .visualization__controls {
	 display: flex;
	 flex-flow: row wrap;
	 width: 100%;
 }

 .visualization__controls__field {
	 width: 25%;
	 max-width: 25%;
	 flex: 1 0 auto;
	 font-size: 0.90em;
 }

 .visualization__controls__field .inner {
	 padding: 5px;
 }

 .visualization__controls__field input {
	 max-width: 100%;
 }

 .visualization__image {
	 width: 100%;
	 height: 240px;
	 border: 1px solid black;
 }

 .visualization__image svg {
	 width: 100%;
	 heigh: 100%;
 }

 .visualization__calculations {
	 display: flex;
	 flex-flow: row wrap;
	 width: 100%;
	 max-width: 100%;
 }

 .visualization__calculations__item {
	 width: 20%;
	 max-width: 20%;
	 flex: 1 0 auto;
	 text-align: center;
	 font-size: 0.9em;
 }

 .visualization__calculations__item .inner {
	 padding-top: 10px;
 }
</style>


<script>
 let width = 600;
 let height = 240;

 // Displays more information if debug is set to 1
 let debug = 0;
 let ifDebug = () => {
	 return debug === 1 ? '' : 'hidden';
 }

 // A bar calculations
 let sizeA = 250;
 let posA = 200;
 $: minA = posA - sizeA/2;
 $: maxA = posA + sizeA/2;
 $: minCA = clamp(minA, 0, width);
 $: maxCA = clamp(maxA, 0, width);
 $: pA = pOf(minA, maxA);
 $: realSizeA = maxCA - minCA;

 // B bar calculations
 let sizeB = 300;
 let posB = 400;
 $: minB = posB - sizeB/2;
 $: maxB = posB + sizeB/2;
 $: minCB = clamp(minB, 0, width);
 $: maxCB = clamp(maxB, 0, width);
 $: pB = pOf(minB, maxB);
 $: realSizeB = maxCB - minCB;

 // Other calculations
 $: intersMinX = Math.min(maxCA, maxCB);
 $: intersMaxX = Math.max(minCA, minCB);
 $: intersectionSize = clamp(intersMinX - intersMaxX, 0, width);
 $: pAgB = (intersectionSize/realSizeB*100).toFixed(1);
 $: pBgA = (intersectionSize/realSizeA*100).toFixed(1);
 $: pOfAandB = (intersectionSize/width*100).toFixed(1);

 // Label positions
 $: aLabelPos = posA-5;
 $: bLabelPos = posB-5;
 $: pOfAandBpos = (intersMaxX+intersectionSize/2)-20

 // Helper functions
 const clamp = (num, min, max) => {
	 return Math.min(Math.max(num, min), max);
 }

 const pOf = (min, max) => {
	 return ((clamp(max, 0, width) - clamp(min, 0, width)) / width * 100).toFixed(1);
 }

 const calculateIntersectionSize = (minA, maxA, minB, maxB) => {
	 return Math.min(maxA, maxB) - Math.max(minA, minB);
 }
</script>

<div class="visualization-wrapper">
	<div class="visualization__controls">
		<div class="visualization__controls__field">
			<div class="inner">
				<label for="posA-range">Position of A</label>
				<input type="range" min="0" max="{width}" bind:value={posA}>
			</div>
		</div>
		<div class="visualization__controls__field">
			<div class="inner">
				<label for="sizeA-range">Size of A</label>
				<input type="range" min="0" max="{width}" bind:value={sizeA}>
			</div>
		</div>
		<div class="visualization__controls__field">
			<div class="inner">
				<label for="posB-range">Position of B</label>
				<input type="range" min="0" max="{width}" bind:value={posB}>
			</div>
		</div>
		<div class="visualization__controls__field">
			<div class="inner">
				<label for="sizeB-range">Size of B</label>
				<input type="range" min="0" max="{width}" bind:value={sizeB}>
			</div>
		</div>
	</div>
	<div class="visualization__image">
		<svg id="svg-vis" viewbox="0 0 {width} {height}">
			<rect x={minA} y=40 width={sizeA} height=10 fill="#48318f"/>
			<rect x={minA} y=50 width={sizeA} height=190 fill="#b8b1f0"/>
			<rect x={minB} y=65 width={sizeB} height=10 fill="#de425b"/>
			<rect x={minB} y=75 width={sizeB} height=165 fill="#ffbbcf"/>
			<rect x={intersMaxX} y=75 width={intersectionSize} height=999 fill="#efaae6"/>

			<text x={aLabelPos} y=35 fill="#48318f">A</text>
			<text x={bLabelPos} y=90 fill="#de425b">B</text>
			{#if intersectionSize > 0}
				<text x={(intersMaxX+intersectionSize/2)-20} y=230 fill="#bf66b6">P(A,B)</text>
			{/if}
		</svg>
	</div>
	<div class="visualization__calculations">
		<div class="visualization__calculations__item">
			<div class="inner">
				P(A): {pA}%
			</div>
		</div>
		<div class="visualization__calculations__item">
			<div class="inner">
				P(B): {pB}%
			</div>
		</div>
		<div class="visualization__calculations__item">
			<div class="inner">
				P(A|B): {pAgB}%
			</div>
		</div>
		<div class="visualization__calculations__item">
			<div class="inner">
				P(B|A): {pBgA}%
			</div>
		</div>
		<div class="visualization__calculations__item">
			<div class="inner">
				P(A,B): {pOfAandB}%
			</div>
		</div>
	</div>
</div>
