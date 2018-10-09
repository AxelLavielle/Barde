import links from "../../assets/data/Links"

export default {
	name: 'DownloadBardeVue',
	data () {
		return {
			"links": links.links
		}
	},
	components : {
	},
	mounted: function () {
		console.log(this.links)
		$('.tooltipped').tooltip();

	},
	methods: {}
}
