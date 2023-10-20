import axiosApi from './AxiosApi.js'
import axios from 'axios';


const apiList = {
  page: {
    method: 'POST',
    url: `/authority/parameter/page`,
  
  },


//---------------------------------------------------------------------------------------
  update: {
    method: 'PUT',
    url: `/authority/parameter`
    //url:'/enc/encupdate'                       //修改
  },


//----------------------------------------------------------------------------------------

  save: {
    method: 'POST',
    url: `/authority/parameter`
    //url:'/enc/encadd'               //新增
  },


  //=====================================================================================
  delete: {
    method: 'DELETE',
    url: `/authority/parameter`
    //url: `/enc/encdelect`                            //删除
  },

  //=====================================================================================
  preview: {
    method: 'POST',
    url: `/authority/parameter/preview`
  },
  export: {
    method: 'POST',
    url: `/authority/parameter/export`
  },
  import: {
    method: 'POST',
    url: `/authority/parameter/import`
    //url:'/enc/encadd'               //新增                                
  }
}






export default {
  page (data, custom = {}) {
    return axiosApi({
      ...apiList.page,
      data,
      custom
    })
  },
  save (data) {
    return axiosApi({
      ...apiList.save,
      data
    })
  },


//--------------------------------------------------------
  update (data) {
    return axiosApi({
      ...apiList.update,
      data
    })
  },

//---------------------------------------------------------


  delete (data) {
   
    return axiosApi({
      ...apiList.delete,
      data
    })
  },
  preview (data) {
    return axiosApi({
      ...apiList.preview,
      data
    })
  },
  export (data) {
    return axiosApi({
      ...apiList.export,
      responseType: "blob",
      data
    })
  },
  import (data) {
    return axiosApi({
      ...apiList.import,
      data
    })                          //新增
  }
}
