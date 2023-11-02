<template>
  <div id="test">
    <el-container>
      <el-aside id="leftMenu" width="330px">
        <el-container direction="vertical">
          <el-card ref="leftMenuCard">
            <el-row style="margin-top:70px">
              <i class="el-icon-video-camera-solid"></i>
              <span id="leftTaskTitle">视频追踪</span>
            </el-row>

            <el-row class="menuInterval">
              <el-button type="info" plain @click="statusUpdate">任务状态（点击刷新）：{{taskStatus[taskIndex]}}</el-button>
            </el-row>

            <el-row class="menuInterval">
              <el-upload
                ref="upload"
                :action=serverUrl
                :file-list="fileList"
                list-type="picture"
                :auto-upload="false"
                :show-file-list="false"
                :on-change="handleUploadFileChange"
                :on-remove="handleUploadFileRemove"
                >
                <el-button slot="trigger" type="plain" icon="el-icon-circle-plus-outline">上传追踪者照片</el-button>
                <el-row class="menuInterval">
                  <el-image :src=traceImage :style="{width: objectImgWidth,height:objectImgHeight}">
                    <div slot="placeholder" class="image-slot">
                      加载中<span class="dot">...</span>
                    </div>
                  </el-image>
                </el-row>
                <el-button type="success" @click="submitUpload"
                class="menuInterval"
                icon="el-icon-upload2"
                :disabled=isSubmitStatus>提交追踪任务</el-button>
                <div slot="tip" class="el-upload__tip">只能上传jpg/png文件，且不超过2MB</div>
              </el-upload>
            </el-row>
            <el-row>
              <el-button @click="test" :disabled=isSubmitStatus>test</el-button>
            </el-row>
          </el-card>
        </el-container>
      </el-aside>

      <el-main>
        <el-card id="mapImageCard" ref="mapImage">
          <el-row class="menuInterval">
              <el-date-picker
                v-model="timeValue"
                type="datetimerange"
                :picker-options="pickerOptions"
                range-separator="至"
                start-placeholder="开始日期"
                end-placeholder="结束日期"
                align="right">
              </el-date-picker>
            </el-row>
          <div :id="index"
            v-for="(item, index) in cameraPos"
            :key="index"
            class="cameraDiv"
            :style="{left:item[0] + 'px', top:item[1] + 'px'}"
            >
            <el-popover
            placement="top-start"
            title=""
            width="200"
            trigger="click"
            >
              <i icon="el-icon-video-camera-solid"></i>
              <el-button
                slot="reference"
                class="camera"
                circle=""
                icon="el-icon-video-camera-solid"
                >
              </el-button>
            </el-popover>
          </div>
        </el-card>
      </el-main>
    </el-container>
  </div>
</template>

<script>
import LeaderLine from 'leader-line'
import moment from 'moment'

export default {
  name: 'TestComponent',
  props: {},
  data() {
    let isTaskBegin = false
    let cameraPos = []
    let mapImageUrl = ''
    let imageList = []
    let fileList = []
    let serverUrl = ''
    let taskStatus = [
      '未开始',
      '正在追踪',
      '已完成'
    ]
    let taskIndex = 0
    let progressPercent = 0
    let timeout = 10000
    let taskID = []
    let intervalList = []
    let traceImage = require('./status.jpeg')
    let objectImgWidth = '245px'
    let objectImgHeight = '300px'
    let objectPicUrl = ''
    let isSubmitStatus = false

      return {isTaskBegin, cameraPos, mapImageUrl, imageList, fileList, serverUrl, taskID, taskStatus, taskIndex, progressPercent, timeout, intervalList, LeaderLine, traceImage,
      objectImgWidth, objectImgHeight, objectPicUrl, isSubmitStatus,
      pickerOptions: {
          shortcuts: [{
            text: '最近一周',
            onClick(picker) {
              const end = new Date();
              const start = new Date();
              start.setTime(start.getTime() - 3600 * 1000 * 24 * 7);
              picker.$emit('pick', [start, end]);
            }
          }, {
            text: '最近一个月',
            onClick(picker) {
              const end = new Date();
              const start = new Date();
              start.setTime(start.getTime() - 3600 * 1000 * 24 * 30);
              picker.$emit('pick', [start, end]);
            }
          }, {
            text: '最近三个月',
            onClick(picker) {
              const end = new Date();
              const start = new Date();
              start.setTime(start.getTime() - 3600 * 1000 * 24 * 90);
              picker.$emit('pick', [start, end]);
            }
          }]
        },
        timeValue: ''
      }
  },

  mounted(){
    this.$refs.leftMenuCard.$el.style.minheight = this.$refs.mapImage.$el.clientHeight + 'px'
  },
  created(){
    console.log('created')
    this.mapImageUrl = this.mapInitiation()
    // console.log('mapImageUrl', this.mapImageUrl)
    this.cameraPos = this.cameraInitiation()
    // console.log('cameraPos', this.cameraPos)
  },

  methods:{
    test(){
      moment
      console.log('time', this.timeValue)
      console.log('start v', this.timeValue[0].valueOf())
      console.log('end v', this.timeValue[1].valueOf())
      console.log('test', moment(this.timeValue[0]).format('YYYY-MM-DD HH:MM:SS'))
      console.log('before', this.isSubmitStatus)
      this.isSubmitStatus = !this.isSubmitStatus
      console.log('after', this.isSubmitStatus)
    },

    cameraInitiation(){
      let camera = [
        [280, 100],
        [950, 200],
        [560, 0],
        [590, 320],
        [760, 10]
      ]

      return camera
    },

    mapInitiation(){
      return require('./map.png')
    },

    createRandom(range, nums){
      let uuid = ''
      for(let i = 0; i < nums; i++){
        let t = Math.floor(Math.random() * range)
        uuid = uuid.concat(t.toString(10))
      }
      // console.log('uuid', uuid)

      return uuid
    },

    trackObject(){
      console.log('trackobject')
      let cameraDom = [document.getElementById('0'),
    document.getElementById('1'),
    document.getElementById('2'),
    document.getElementById('3'),
    document.getElementById('4')]

    console.log('cameraDom', cameraDom)

    let pos = [0, 3, 4, 1, 2]
    for(let i = 0; i < 4; i++){
      new LeaderLine(LeaderLine.pointAnchor(cameraDom[pos[i]],{
        x: 70,
        y: 30
      }),
      LeaderLine.pointAnchor(cameraDom[pos[i + 1]],{
        x: -10,
        y: 30
      }),
      {color: 'red', size: 8})
    }

    console.log('down.......')

      return true
    },

    async uploadAttachment(params){
      await this.$axios.post('api/file/file/anyone/upload', params,{
        headers:{
          'Content-Type': 'multipart/form-data'
        }
      }).then(response=>{
        console.log('success', response)
        this.objectPicUrl = response.data.data.url.substring(response.data.data.url.length + 1, response.data.data.url.indexOf("group"))
      }).catch(error=>{
        console.log('error', error)
        this.isSubmitStatus = !this.isSubmitStatus
      });
    },

      async releaseTask(params){
      console.log('release task', params)
      await this.$axios.post('api/task/release/task', params, {
        headers: {
          'Content-Type': 'application/x-www-form-urlencoded'
        }
      }).then(response=>{
        console.log('success', response)
        this.isSubmitStatus = true
        this.taskIndex = 1
        this.$message({
          message: '追踪任务提交成功！请勿离开当前页面否则任务失败！',
          type: 'success'
        })
        // this.taskID.push(tmpTaskID)
      }).catch(error=>{
        console.log('error', error)
        this.isSubmitStatus = !this.isSubmitStatus
      });
    },

    async createTask(tmpFileList){
      console.log('createTask')
      console.log('tmpFileList', tmpFileList)

      this.isSubmitStatus = !this.isSubmitStatus
      // 创建追踪任务前先上传追踪者图片,第一步准备接口参数
      let formData = new FormData()
      formData.append('file', tmpFileList[0].raw)
      formData.append('bizType', 'filetransfer')
      formData.append('bucket', 'filetransfer')
      formData.append('storageType', 'FAST_DFS')
      // 使用同步请求上传附件
      await this.uploadAttachment(formData)

      console.log('objectPicUrl', this.objectPicUrl)

      // 发布任务
      let params = {
      'end': '2023-09-14 09:59:33',
      'start': '2023-09-14 09:50:33',
      'url': this.objectPicUrl
      }

      await this.releaseTask(params)
      console.log('down ...................')
    },

    statusUpdate(){
      console.log('statusUpdate')

      if(this.taskStatus[this.taskIndex] == '未开始'){
        this.$message.error("任务未提交！请检查上传的照片！")
        return
      }

      if(this.taskStatus[this.taskIndex] == '已完成'){
        this.$message({
          message: '刷新成功！任务已完成！请查看视频轨迹！',
          type: 'success'
        })
        this.trackObject()
      }
      else{
        let t = this.getTaskResult()
        console.log('get task', t)
      }
    },

    getTaskResult(){
      console.log('getTaskResult')

      this.$axios.get("api/task/release/reidImgRes")
      .then(response=>{
        console.log('success................', response)
        this.taskIndex = 2
        this.statusUpdate()
      }).catch(error=>{
        console.log('error', error)
        this.$message.error('刷新成功！任务还未完成！请稍后！')
      });
    },

    handleUploadFileChange(file, fileList){
      console.log('handleUploadFileChange', file)
      this.fileList = fileList
      this.traceImage = file.url
    },

    handleUploadFileRemove(file, fileList){
      console.log('handleUploadFileRemove', file)
      this.fileList = fileList
    },

    submitUpload(){
      console.log('submit task')
      console.log('fileList', this.fileList)
      if(this.fileList.length <= 0){
        this.$message.error('开始追踪任务前请提交追踪者照片！')
        return
      }

      this.createTask(this.fileList)

      // if(this.taskID.size() != 0)
      //   this.taskID.push(tmpTaskID)
      // }
      console.log('create down. taskID ', this.taskID)
    },
  },
}
</script>

<style scoped>
#test{
  font-family: "Helvetica Neue",Helvetica,"PingFang SC","Hiragino Sans GB","Microsoft YaHei","微软雅黑",Arial,sans-serif;
}

/* left menu */
#leftMenu{
  padding: 20px;
}

.menuInterval{
  margin-top: 30px;
}

/* map */
#mapImageCard{
  width: 99%;
  height: calc(100vh - 100px);
  background-image: url("./map.png");
  background-size: cover;
  background-repeat: no-repeat;
}

#headerMenuCard{
  width: 100%;
  font-size: 20px;
  margin: 20px 20px 0 20px;
}

#headerMenu{
  text-align: left;
  padding: 0;
}

.camera{
  position: relative;
  font-size: 40px;
}

.cameraDiv{
  position: relative;
  display: block;
  width: 100%;
  height: 100%;
  z-index: 90;
}

.leader-line{
  z-index: 999
}
</style>
