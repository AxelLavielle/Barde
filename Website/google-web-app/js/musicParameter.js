export default class musicParameter {

	constructor(name, value, selected) {
		this.name = value;
		this.value = value;
		this.selected = selected;
	}

	getName(){
		return this.name
	}

	getValue(){
		return this.value
	}

	isSelected(){
		return this.selected
	}

}